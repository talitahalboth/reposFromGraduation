import numpy as np
import matplotlib.pyplot as plt
import statistics

f = open("w2v_1000_30.txt", "r")

lines = f.readlines()


class Result:
    def __init__(self, min_count, window):
        self.min_count = min_count
        self.window = window
        self.averageScore = 0
        self.averageF1Score = 0
        self.averageLoss = 0

        self.scores = []
        self.f1scores = []
        self.loss = []

        # self.median = 0

    @property
    def median(self):
        return statistics.median(self.scores)

    def __lt__(self, other):
        return self.median < other.median

    def __le__(self, other):
        return self.median <= other.median

    def __gt__(self, other):
        return self.median > other.median

    def __ge__(self, other):
        return self.median >= other.median


def readMinCountWindow(line):
    val = line.split(" ")[1][:-1]
    return int(val)


def readAvg(line):
    val = line.split(" ")[2][:-1]
    return float(val)


def readArray(line):
    lista = line.split("[")[1][:-2]
    x = np.array(lista.split(","))
    lista = np.asfarray(x, float)
    return lista


results = []
for calc in range(30):
    newResult = Result(0, 0)
    for i in range(16):
        if i == 0:
            newResult.min_count = readMinCountWindow(lines[calc * 16 + i])
        if i == 1:
            newResult.window = readMinCountWindow(lines[calc * 16 + i])
        if i == 3:
            newResult.averageScore = readAvg(lines[calc * 16 + i])
        if i == 7:
            newResult.averageLoss = readAvg(lines[calc * 16 + i])
        if i == 11:
            newResult.averageF1Score = readAvg(lines[calc * 16 + i])
        if i == 5:
            newResult.scores = readArray(lines[calc * 16 + i])
        if i == 9:
            newResult.loss = readArray(lines[calc * 16 + i])
        if i == 13:
            newResult.f1scores = readArray(lines[calc * 16 + i])
    # print(newResult.f1scores)
    results.append(newResult)
results.sort()

windowList = {}
minCountList = {}
windows = []
mincounts = []
for result in results:
    if result.min_count not in minCountList:
        mincounts.append(result.min_count)
        minCountList[result.min_count] =[]
    minCountList[result.min_count].append(result.averageScore)
    if result.window not in windowList:
        windows.append(result.window)
        windowList[result.window] = []
    windowList[result.window].append(result.averageScore)

windowsAverage = {}
for window in windows:
    windowsAverage[window] = statistics.mean(windowList[window])
mincountsAverage = {}
for mincount in mincounts:
    mincountsAverage[mincount] = statistics.mean(minCountList[mincount])
windowsAverage = {k: v for k, v in sorted(windowsAverage.items(), key=lambda item: item[1])}
print(windowsAverage)
mincountsAverage = {k: v for k, v in sorted(mincountsAverage.items(), key=lambda item: item[1])}
print(mincountsAverage)
print(mincountsAverage.keys())
plt.rcParams["figure.figsize"] = (3, 3)
figScore, axScore = plt.subplots()
xTicks = []
for i in range(1, len(windowsAverage.values())+1):
    xTicks.append(i)
axScore.scatter(xTicks, windowsAverage.values())
x = xTicks
plt.xticks(x,list(windowsAverage.keys()))
plt.title('Scores window')
# plt.show()
outfile = 'scores-window-w2v' + '.pdf'
plt.savefig(outfile, dpi=300, bbox_inches='tight')


plt.rcParams["figure.figsize"] = (3, 3)
figScore, axScore = plt.subplots()
xTicks = []
for i in range(1, len(mincountsAverage.values())+1):
    xTicks.append(i)
axScore.scatter(xTicks, mincountsAverage.values())
x = xTicks
plt.xticks(x,list(mincountsAverage.keys()))
plt.title('Scores min count')
# plt.show()
outfile = 'scores-min-count-w2v' + '.pdf'
plt.savefig(outfile, dpi=300, bbox_inches='tight')


def boxPlot(results):
    minCountAndWindow = []
    allScores = []
    allF1Scores = []
    allLoss = []
    for res in results:
        print(res.min_count, res.window)
        print(res.averageScore)
        minCountAndWindow.append([res.min_count, res.window])
        allScores.append(res.scores)
        allF1Scores.append(res.f1scores)
        allLoss.append(res.loss)

    figScore, axScore = plt.subplots()
    axScore.set_title('Scores')
    axScore.boxplot(allScores)

    xTicks = []
    for i in range(1, len(results) + 1):
        xTicks.append(i)
    x = xTicks
    plt.xticks(x, minCountAndWindow, rotation=90)
    plt.title('Scores')
    # plt.show()
    outfile = 'scores-w2v-boxplot' + '.pdf'
    plt.savefig(outfile, dpi=500, bbox_inches='tight')

    figF1Score, axF1Score = plt.subplots()
    axF1Score.set_title('F1 Scores')
    axF1Score.boxplot(allF1Scores)

    plt.xticks(x, minCountAndWindow, rotation=90)
    plt.title('F1 Scores')
    # plt.show()
    outfile = 'f1Scores-w2v-boxplot' + '.pdf'
    plt.savefig(outfile, dpi=500, bbox_inches='tight')

    figLoss, axLoss = plt.subplots()
    axLoss.set_title('Losses')
    axLoss.boxplot(allLoss)
    plt.xticks(x, minCountAndWindow, rotation=90)
    plt.title('Loss')
    # plt.show()
    outfile = 'loss-w2v-boxplot' + '.pdf'
    plt.savefig(outfile, dpi=500, bbox_inches='tight')


def averagePLot(results):
    minCountAndWindow = []
    scores = []
    f1scres = []
    loss = []
    count = 1
    for res in results:
        print(res.min_count, res.window)
        print(res.averageScore)
        minCountAndWindow.append([res.min_count, res.window])
        scores.append(res.averageScore)
        f1scres.append(res.averageF1Score)
        loss.append(res.averageLoss)

    figScore, axScore = plt.subplots()
    axScore.set_title('Scores')

    xTicks = []
    for i in range(1, len(results) + 1):
        xTicks.append(i)
    axScore.scatter(xTicks, scores)
    x = xTicks
    plt.xticks(x, minCountAndWindow, rotation=90)
    plt.title('Scores')
    # plt.show()
    outfile = 'scores-w2v' + '.pdf'
    plt.savefig(outfile, dpi=500, bbox_inches='tight')

    figF1Score, axF1Score = plt.subplots()
    axF1Score.set_title('F1 Scores')
    axF1Score.scatter(xTicks, f1scres)

    plt.xticks(x, minCountAndWindow, rotation=90)
    plt.title('F1 Scores')
    # plt.show()
    outfile = 'f1Scores-w2v' + '.pdf'
    plt.savefig(outfile, dpi=500, bbox_inches='tight')

    figLoss, axLoss = plt.subplots()
    axLoss.set_title('Losses')
    axLoss.scatter(xTicks, loss)
    plt.xticks(x, minCountAndWindow, rotation=90)
    plt.title('Loss')
    # plt.show()
    outfile = 'loss-w2v' + '.pdf'
    plt.savefig(outfile, dpi=500, bbox_inches='tight')


# boxPlot(results)
