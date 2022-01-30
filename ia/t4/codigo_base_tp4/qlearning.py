import util
import random
import matplotlib.pyplot as plt
import numpy as np


class Agente:
    def __init__(self, env, epsilon=0.01, alpha=0.8, gamma=0.2):
        self.epsilon = epsilon  # exploracao
        self.alpha = alpha  # taxa de aprendizado
        self.gamma = gamma  # desconto
        self.env = env  # ambiente

        "*** SEU CODIGO AQUI ***"
        self.Q = np.zeros((env.env.observation_space.n, env.env.action_space.n))
        self.decayRate = .999
        self.episodeCount = 0
        self.minEpsilon = .1

    def escolheAcao(self, state):
        '''
        Metodo que deve retornar uma acao a partir de um estado
        '''
        actions = self.env.getLegalActions(state)
        "*** SEU CODIGO AQUI ***"
        if np.random.uniform(0, 1) < self.epsilon:
            return random.choice(actions)
        else:
            return np.argmax(self.Q[state, :])

    def atualizaAgente(self, state, action, reward, next_state):
        '''
        Metodo chamado apos executar cada acao durante o treinamento
        '''

        "*** SEU CODIGO AQUI ***"
        amostra = reward + self.gamma * np.max(self.Q[next_state, :])
        self.Q[state, action] = (1 - self.alpha) * self.Q[state, action] + self.alpha * amostra

        pass

    def novoEpisodio(self, is_train=True):

        '''
        Metodo chamado ao fim de cada episodio.
        A variavel is_train ira indicar se eh um episodio de treinamento
        '''

        "*** SEU CODIGO AQUI ***"
        if is_train:
            self.episodeCount += 1
            if self.episodeCount % 10 == 0:
                self.epsilon *= self.decayRate
                # print(self.epsilon)
                self.epsilon = max(self.epsilon, self.minEpsilon)
        "*** (Eh possivel que a sua implementacao nao utilize este metodo) ***"
        pass
