import matplotlib.pyplot as plt
import statistics

dir = "..\\results\\"
baseFileName = "..\\results\\result"
extension = "-eps-decayyyy"
print(baseFileName)
epsilons = [0.5, 0.9, 0.98]
maxTraining = [5000, 10000]

allTraining = []
averageTraining = []
allValidating = []
averageValidation = []
xticksLabels = []
xticks = []
count = 1
for epsilon in epsilons:
    for training in maxTraining:
        # result-1000-0.5-episodes-test
        # f = open(baseFileName + '-' + str(training) + '-' + str(epsilon) + extension + '.txt', 'r')
        f = open(dir+"bestDecay")
        lines = f.readlines()
        treinamento = []
        validacao = []
        par = False
        for line in lines:

            rate = line.split(' ')[-1]
            splitRate = rate.split('/')
            rate = int(splitRate[0]) / (1.0 * int(splitRate[1]))
            if not par:
                treinamento.append(rate)
            else:
                validacao.append(rate)
            par = not par
        print(epsilon, training)
        print(statistics.mean(treinamento))
        print(statistics.mean(validacao))
        allTraining.append(treinamento)
        allValidating.append(validacao)
        averageTraining.append(statistics.mean(treinamento))
        averageValidation.append(statistics.mean(validacao))

        xticksLabels.append(str(epsilon)+", " + str(training))
        xticks.append(count)
        count += 1

        # plot scatter
        # correlation, axCorrelation = plt.subplots()
        #
        # axCorrelation.set_title("Traininig vs Validation")
        # axCorrelation.scatter(treinamento, validacao, label=[epsilon, training])
        # plt.savefig("trainingVsValidation" + '-' + str(training) + '-' + str(epsilon) + extension + ".pdf")
        # plt.clf()


def boxplot(allTrainings, allValidation, xticks, xticksLabels):
    # axCorrelation.legend()
    # plt.savefig("trainingVsValidation.pdf")
    # plt.clf()

    fig1, ax1 = plt.subplots()
    ax1.set_title('Training')
    ax1.boxplot(allTrainings)
    plt.xticks(ticks=xticks, labels=xticksLabels, rotation=45)
    fig1.subplots_adjust(
        top=0.9,
        bottom=0.2,
        left=0.08,
        right=0.981,
        hspace=0.2,
        wspace=0.2
    )
    plt.savefig("training-box" + extension + ".pdf")
    fig1, ax1 = plt.subplots()
    ax1.set_title('Validation')
    ax1.boxplot(allValidation)
    plt.xticks(ticks=xticks, labels=xticksLabels, rotation=45)
    fig1.subplots_adjust(
        top=0.9,
        bottom=0.2,
        left=0.08,
        right=0.981,
        hspace=0.2,
        wspace=0.2
    )
    plt.savefig("validation-box" + extension + ".pdf")


def plotAverages(avgTraining, avgValidation, xticks, xticksLabels):
    # axCorrelation.legend()
    # plt.savefig("trainingVsValidation.pdf")
    # plt.clf()

    fig1, ax1 = plt.subplots()
    ax1.set_title('Training')
    print(avgTraining, xticksLabels)
    ax1.scatter(xticksLabels, avgTraining)
    # plt.xticks(ticks=xticks, labels=xticksLabels, rotation=45)
    fig1.subplots_adjust(
        top=0.9,
        bottom=0.2,
        left=0.08,
        right=0.981,
        hspace=0.2,
        wspace=0.2
    )
    plt.show()
    plt.savefig("training" + extension + ".pdf")

    fig2, ax2 = plt.subplots()
    ax2.set_title('Validation')

    ax2.scatter(xticksLabels, avgValidation)
    # plt.xticks(ticks=xticks, labels=xticksLabels, rotation=45)
    fig2.subplots_adjust(
        top=0.9,
        bottom=0.2,
        left=0.08,
        right=0.981,
        hspace=0.2,
        wspace=0.2
    )
    plt.savefig("validation" + extension + ".pdf")
    plt.show()


# plotAverages(averageTraining, averageValidation, xticks, xticksLabels)
# boxplot(allTraining, allValidating, xticks, xticksLabels)