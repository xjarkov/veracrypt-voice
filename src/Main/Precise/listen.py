#!/usr/bin/env python3

import os
import sys
import time

from threading import Event

from precise.network_runner import Listener
from runner.precise_runner import PreciseRunner
from runner.precise_runner.runner import ListenerEngine


def main():
    os.chdir(os.getcwd() + "/Precise")

    def on_activation():
        print("activated")

    listener = Listener("model.net", 2048)

    engine = ListenerEngine(listener, 2048)
    runner = PreciseRunner(engine, 3, sensitivity = 0.5, on_activation = on_activation)

    runner.start()
    while True:
        line = sys.stdin.readline().rstrip()
        print("line control")


if __name__ == '__main__':
    main()
