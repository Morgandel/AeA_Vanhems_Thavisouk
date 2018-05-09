successeurs = [[1,2],[2],[0],[2]]
N=len(successeurs)
d=4/5
score = [1/N]*N

def getPredecessor(succ):
    pred=[]
    for i in range(len(succ)):
        pred.append([])
    for i,l in enumerate(succ):
        for j in l:
            pred[j].append(i)
    return pred

def calcScore(pred, succ, current):
    sum=0
    for j in range(0,len(pred[current])):
        nbSucc = len(succ[pred[current][j]])
        if(nbSucc !=0):
            sum += score[pred[current][j]]/nbSucc
    return d * sum + (1-d) * 1/N

def algo(succ, pred):
    for i in range(0,30):
        for j in range(0,N):
            score[j] = calcScore(pred, succ, j)
    total=0
    for i in range(0,N):
        print(i,":", score[i])
        total+=score[i]
    print(total)

if __name__ == '__main__':
    predecesseur = getPredecessor(successeurs)
    algo(successeurs,predecesseur)
