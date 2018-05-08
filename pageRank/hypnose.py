successeurs = [[],[0,2],[3],[1],[0,5],[6],[4]]
predecesseur = [[1,4],[3],[1],[2],[6],[4],[5]]
N=len(successeurs)
d=4/5
score = [1/N]*N

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
    for i in range(0,N):
        print(i,":", score[i])


if __name__ == '__main__':
    algo(successeurs,predecesseur)
