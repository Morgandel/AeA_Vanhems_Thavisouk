from random import random
import time

def nextFit(sequence):
    lesBoites=[[]]
    iBoites=0
    espace=0
    for i,o in enumerate(sequence):
        espace=espace+o
        if(espace>1):
            lesBoites.append([i])
            iBoites=iBoites+1
            espace=o
        else:
            lesBoites[iBoites].append(i)
    return lesBoites

def firstFit(sequence):
    lesBoites=[[]]
    iBoites=0
    espaceBoites=[0]
    for i,o in enumerate(sequence):
        added=False
        for j,t in enumerate(espaceBoites):
            if(t+o<=1):
                added=True
                espaceBoites[j] += o
                lesBoites[j].append(i)
                continue;
        if(not added):
            espaceBoites.append(o)
            lesBoites.append([i])
    return lesBoites

def bestFit(sequence):
    lesBoites=[[]]
    iBoites=0
    espaceBoites=[0]
    for i,o in enumerate(sequence):
        iBest=0
        tBest=-10
        added=False
        for j,t in enumerate(espaceBoites):
            if(t+o>tBest and t+o<=1):
                if(t+o==1):
                    added=True
                    espaceBoites[j] += o
                    lesBoites[j].append(i)
                    continue;
                iBest=j
                tBest=t+o
                added=True
        if(not added):
            espaceBoites.append(o)
            lesBoites.append([i])
        else:
            espaceBoites[iBest] += o
            lesBoites[iBest].append(i)
    return lesBoites

def online(sequence,printLen):
    #print(sequence)
    if(not printLen):
        retour=[]
        seqLen=len(sequence)
        start = time.time()
        l=len(nextFit(sequence))
        end = time.time()
        retour.append((seqLen,l,end - start))
        start = time.time()
        l=len(firstFit(sequence))
        end = time.time()
        retour.append((seqLen,l,end - start))
        start = time.time()
        l=len(bestFit(sequence))
        end = time.time()
        retour.append((seqLen,l,end - start))
        return retour
    else:
        print("Version Online\n====================\n")
        start = time.time()
        l=len(nextFit(sequence))
        end = time.time()
        print("NextFit:","number of Boxes",l,"Time",end - start)
        start = time.time()
        l=len(firstFit(sequence))
        end = time.time()
        print("FirstFit:","number of Boxes",l,"Time",end - start)
        start = time.time()
        l=len(bestFit(sequence))
        end = time.time()
        print("BestFit:","number of Boxes",l,"Time",end - start)
    print()

def offline(sequence,inv,printLen):

    start = time.time()
    if(inv):
        sortedSeq=sorted(sequence,reverse=True)
    else:
        sortedSeq=sorted(sequence)
    end = time.time()
    tempsTri=end - start
    #print(sortedSeq)
    if(printLen):
        if(inv):
            print("Version Offline Reverse\n====================\n")
        else:
                print("Version Offline\n====================\n")
        start = time.time()
        l=len(nextFit(sortedSeq))
        end = time.time()
        print("NextFit:","number of Boxes",l,"Time",(end - start) + tempsTri)
        start = time.time()
        l=len(firstFit(sortedSeq))
        end = time.time()
        print("FirstFit:","number of Boxes",l,"Time",(end - start) + tempsTri)
        start = time.time()
        l=len(bestFit(sortedSeq))
        end = time.time()
        print("BestFit:","number of Boxes",l,"Time",(end - start) + tempsTri)
    else:
        retour=[]
        seqLen=len(sortedSeq)
        start = time.time()
        l=len(nextFit(sortedSeq))
        end = time.time()
        retour.append((seqLen,l,(end - start) + tempsTri))
        start = time.time()
        l=len(firstFit(sortedSeq))
        end = time.time()
        retour.append((seqLen,l,(end - start) + tempsTri))
        start = time.time()
        l=len(bestFit(sortedSeq))
        end = time.time()
        retour.append((seqLen,l,(end - start) + tempsTri))
        return retour
    print()

def write_file(message,fileName, mode):
    file = open(fileName,mode)
    file.write(message)
    file.close()

def writeData(name,sequence):
    box=""
    time=""
    for i in sequence:
        box+=str(i[0][0])+", "+str(i[0][1])+", "+str(i[1][1])+", "+str(i[2][1])+"\n"
        time+=str(i[0][0])+", "+str(i[0][2])+", "+str(i[1][2])+", "+str(i[2][2])+"\n"
    write_file(box,"nbBox"+name+".dat")
    write_file(time,"time"+name+".dat")

if __name__ == '__main__':

    onlineSeq=[]
    offlineSeq=[]
    offlineRevSeq=[]
    sequence=dict()
    N=20000
    for i in range(1000,N,1000):
        sequence[i]=[]
        for j in range(i):
            sequence[i].append(round(random(),2))
    for i in range(1000,N,1000):
        onlineSeq.append(online(sequence[i],False))
        offlineSeq.append(offline(sequence[i],False,False))
        offlineRevSeq.append(offline(sequence[i],True,False))

    #writeData("",onlineSeq)
    #writeData("Offline",offlineSeq)
    #writeData("OfflineRev",offlineRevSeq)
