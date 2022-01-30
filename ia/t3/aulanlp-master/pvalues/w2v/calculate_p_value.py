from scipy import stats
import statistics
import numpy as np
arquivo = "losses"
file1 = open(arquivo, 'r')
Lines = file1.readlines()
original =       "All words       "
removingWords = ["90\% mais usadas", "80\% mais usadas", "70\% mais usadas",
                 "30\% menos usadas", "20\% menos usadas", "10\% menos usadas"]
originalRes = Lines[0].split(' ')
x = np.array(originalRes)
originalRes = np.asfarray(x, float)
saida = open("pvalues"+arquivo+"latex", "w")
for i in range(len(removingWords)):
    newScore = Lines[i+1].split(' ')
    x = np.array(newScore)
    newScore = np.asfarray(x, float)
    # print(stats.ttest_ind(originalRes, newScore[i], equal_var=False))
    res = 0
    if statistics.mean(originalRes) > statistics.mean(newScore):
        res = (stats.ttest_ind(originalRes, newScore, equal_var=False, alternative='greater'))
    else:

        res = (stats.ttest_ind(originalRes, newScore, equal_var=False, alternative='less'))

    print(original, "%0.8f" % statistics.mean(originalRes))
    print(removingWords[i], "%0.8f" % statistics.mean(newScore))
    print(res.statistic)
    print(res.pvalue)
    print()
    saida.write(removingWords[i] +" & " + str("%0.8f" % statistics.mean(newScore))+" & " + str("%0.4f" % res.statistic) +" & " + str("%0.4f" % res.pvalue) + "\\\\ \n")
