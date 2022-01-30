from datetime import datetime

import gym
import numpy as np
import matplotlib.pyplot as plt
import random
import argparse
import os
import time

from qlearning import Agente

np.random.seed(0)
random.seed(42)


class FrozenLakeEnv():
    def __init__(self, env):
        self.env = env

    def getLegalActions(self, state):
        return list(range(int(env.action_space.n)))

    def getStateSpaceSize(self):
        return int(self.env.observation_space.n)

    def getActionSpaceSize(self):
        return int(self.env.action_space.n)


def plotHistory(steps_per_episode, w=10, title='', plt_show=True,
                x_title="", y_title=""):
    plt.figure()
    plt.plot([np.mean(steps_per_episode[i:i + w]) for i in
              range(0, len(steps_per_episode), w)])
    plt.title(title)

    plt.xlabel(x_title)
    plt.ylabel(y_title)
    if plt_show:
        plt.show()


def checkStep(args):
    cmd = input()
    if cmd == 's':
        args.silent = True
    elif cmd == 'p':
        os.system('clear')
    elif cmd == '\'':
        print(bytes.fromhex('512d4c6f7563757261').decode('utf-8'))
    return cmd


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-tr", "--train_episodes", default=1000,
                        help="maximum of trainning episodes",
                        required=False, dest="train_episodes", type=int)
    parser.add_argument("-vl", "--val_episodes", default=1000,
                        help="total of episodes simulated without training",
                        required=False, dest="val_episodes", type=int)
    parser.add_argument("-e", "--epsilon", default=0.5, required=False,
                        dest="epsilon", type=float)
    parser.add_argument("-a", "--alpha", default=0.1, required=False,
                        dest="alpha", type=float)
    parser.add_argument("-g", "--gamma", default=0.99, required=False,
                        dest="gamma", type=float)
    parser.add_argument("-p", "--plot", dest="plot", default=False,
                        action='store_true')
    parser.add_argument('-v', '--verbose', dest="verbose", action='store_true',
                        default=False)
    parser.add_argument('-s', '--silent', dest="silent", action='store_true',
                        default=False)

    parser.add_argument('-d', '--disable_slippery', dest="disable_slippery",
                        action='store_true', default=False)

    parser.add_argument('-r', '--random_seed', dest="random_seed",
                        action='store_true', default=False)



    args = parser.parse_args()

    env = gym.make('FrozenLake-v0', is_slippery=not args.disable_slippery)

    env.seed(0)
    if args.random_seed:
        now = int(datetime.now().timestamp() * 1000) % 10000
        np.random.seed(now)
        random.seed(now)


    agent = Agente(FrozenLakeEnv(env), epsilon=args.epsilon, alpha=args.alpha,
                   gamma=args.gamma)

    total_episodes = args.train_episodes + args.val_episodes + 1
    episode_start_val = args.train_episodes + 1
    train_timesteps_list = []
    val_timesteps_list = []

    total_reward = 0
    cmd = None

    for i_episode in range(1, total_episodes):
        state = env.reset()
        done = 0
        t = 0
        reward = 0

        if i_episode >= episode_start_val:
            agent.epsilon = 0.0

        if i_episode == episode_start_val:
            print("Taxa de sucesso no treinamento: {}/{}".format(int(total_reward), args.train_episodes))
            total_reward = 0

        if i_episode >= episode_start_val and not args.silent:
            if cmd == 'p':
                os.system('clear')
            print("Testando: use a tecla enter para executar o próximo passo, 'p' para jogar " +
                  "todas os passos restantes, 's' para parar de imprimir na tela e 'q' para sair do programa", end="")
            env.render()
            print()
            cmd = checkStep(args)
            if cmd == 'q':
                break

        while not done:
            action = agent.escolheAcao(state)

            last_state = state
            state, reward, done, info = env.step(action)
            total_reward += reward

            if i_episode >= episode_start_val and not args.silent:
                if cmd == 'p':
                    time.sleep(.1)
                    os.system('clear')
                    print("Última recompensa imediata: {}".format(reward))
                    env.render()
                elif t >= 0:
                    print("Testando: use a tecla enter para executar o próximo passo, 'p' " +
                          "para jogar todas os passos restantes, 's' para parar de imprimir na tela")
                    print("Última recompensa imediata: {}".format(reward))
                    env.render()
                    cmd = checkStep(args)

            if i_episode < episode_start_val:
                agent.atualizaAgente(last_state, action, reward, state)
            t += 1

        if i_episode >= episode_start_val:
            val_timesteps_list.append(t)
        else:
            train_timesteps_list.append(t)

        # Prevent flood log information when training
        if i_episode >= episode_start_val:
            if not args.silent:
                print("Episódio {} acabou após {} passos".format(
                    i_episode, t))
                if cmd == 'p':
                    time.sleep(1)
        elif args.verbose:
            print("\rEpisódio {} acabou após {} passos".format(
                i_episode, t), end='\r')

        agent.novoEpisodio(is_train=(i_episode < episode_start_val))

    env.close()
    print("Taxa de sucesso na validação : {}/{}".format(int(total_reward), args.val_episodes))
    if args.plot:
        x_title = "Episódios (agrupados de 10 em 10)"
        y_title = "Número médio de passos executados nos 10 episódios"

        title = 'Treinamento - {} Episódios - Epsilon {}'.format(
            args.train_episodes, args.epsilon)
        plotHistory(train_timesteps_list, 10, title=title,
                    plt_show=False,
                    x_title=x_title, y_title=y_title)

        title = 'Validação - {} Episódios - Epsilon {}'.format(
            args.val_episodes, args.epsilon)
        plotHistory(val_timesteps_list, 10, title=title,
                    x_title=x_title, y_title=y_title)
