#!/usr/bin/env python3

import numpy as np
from os.path import join
import os
import sys

from shutil import get_terminal_size
from prettyparse import create_parser
from random import randint

from precise.network_runner import Listener
from runner.precise_runner import PreciseRunner
from runner.precise_runner.runner import ListenerEngine
from precise.util import save_audio, buffer_to_audio

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
        print("activated\n", flush=True)

    def on_prediction(conf):
        max_width = 80
        width = min(get_terminal_size()[0], max_width)
        units = int(round(conf * width))
        bar = 'X' * units + '-' * (width - units)
        cutoff = round((1.0 - args.sensitivity) * width)
        print(bar[:cutoff] + bar[cutoff:].replace('X', 'x'))

    def get_prediction(chunk):
        nonlocal audio_buffer
        audio = buffer_to_audio(chunk)
        audio_buffer = np.concatenate((audio_buffer[len(audio):], audio))
        return listener.update(chunk)

    while True:
        line = sys.stdin.readline().rstrip()
        if (line == "start"):
            listener = Listener(args.model, args.chunk_size)
            audio_buffer = np.zeros(listener.pr.buffer_samples, dtype=float)
            engine = ListenerEngine(listener, args.chunk_size)
            engine.get_prediction = get_prediction;
            runner = PreciseRunner(engine, args.trigger_level, sensitivity = args.sensitivity, on_activation = on_activation)
            runner.start()
        elif (line == "stop"):
            runner.stop()
        elif (line == "running"):
            print(runner.running)


if __name__ == '__main__':
    main()
