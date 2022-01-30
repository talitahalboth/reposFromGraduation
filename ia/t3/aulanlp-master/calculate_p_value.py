from scipy import stats
import statistics
import numpy as np

original = "All words                    "
removingWords = ["Remove words used 90% or more", "Remove words used 80% or more", "Remove words used 70% or more",
                 "Remove words used 30% or less", "Remove words used 20% or less", "Remove words used 10% or less"]
originalRes = input().split(' ')
x = np.array(originalRes)
originalRes = np.asfarray(x, float)

for i in range(len(removingWords)):
    newScore = input().split(' ')
    x = np.array(newScore)
    newScore = np.asfarray(x, float)
    print(original, "%0.4f" % statistics.mean(originalRes))
    print(removingWords[i], "%0.4f" % statistics.mean(newScore))
    # print(stats.ttest_ind(originalRes, newScore[i], equal_var=False))
    res = 0
    if statistics.mean(originalRes) > statistics.mean(newScore):
        res = (stats.ttest_ind(originalRes, newScore, equal_var=False, alternative='greater'))
    else:

        res = (stats.ttest_ind(originalRes, newScore, equal_var=False, alternative='less'))
    print(res.statistic)
    print(res.pvalue)
    print()
