#!/usr/bin/env python3

import numpy as np
from os.path import join
import os
import sys

from prettyparse import create_parser
from random import randint

from precise.network_runner import Listener
from runner.precise_runner import PreciseRunner
from runner.precise_runner.runner import ListenerEngine
from precise.util import save_audio

usage = '''
    Run a model on microphone audio input
    
    :model str
        Either Keras (.net) or TensorFlow (.pb) model to run
    
    :-c --chunk-size int 2048
        Samples between inferences
    
    :-l --trigger-level int 3
        Number of activated chunks to cause an activation
    
    :-s --sensitivity float 0.5
        Network output required to be considered activated

    :-d --save-dir str -
        Folder to save false positives
'''

session_id, chunk_num = '%09d' % randint(0, 999999999), 0


def main():
    args = create_parser(usage).parse_args()
    os.chdir(os.getcwd() + "/Precise")

    def on_activation():
        print("activated")
        if args.save_dir:
            global chunk_num
            nm = join(args.save_dir, args.save_prefix + session_id + '.' + str(chunk_num) + '.wav')
            save_audio(nm, audio_buffer)
            print()
            print('Saved to ' + nm + '.')
            chunk_num += 1

    while True:
        line = sys.stdin.readline().rstrip()
        if (line == "start"):
            listener = Listener("model.net", 2048)
            audio_buffer = np.zeros(listener.pr.buffer_samples, dtype=float)
            engine = ListenerEngine(listener, 2048)
            runner = PreciseRunner(engine, 3, sensitivity = 0.5, on_activation = on_activation)
            runner.start()
        elif (line == "stop"):
            runner.stop()
        elif (line == "running"):
            print(runner.running)


if __name__ == '__main__':
    main()
