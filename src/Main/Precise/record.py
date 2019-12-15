#!/usr/bin/env python3
# Copyright 2019 Mycroft AI Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
from os.path import isfile
import os
import pyaudio
import select
import sys
import wave


def record(p):
    chunk_size = 1024
    stream = p.open(format=p.get_format_from_width(2), channels=1,
                    rate=16000, input=True, frames_per_buffer=chunk_size)

    frames = []
    while True:
        frames.append(stream.read(chunk_size))
        if select.select([sys.stdin,],[],[],0.0)[0]:
            if sys.stdin.readline().rstrip() == "terminate":
                break;
            
    stream.stop_stream()
    stream.close()

    return b''.join(frames)


def saveAudio(name, data):
    wf = wave.open(name, 'wb')
    wf.setnchannels(1)
    wf.setsampwidth(2)
    wf.setframerate(16000)
    wf.writeframes(data)
    wf.close()


def nextName(name):
    name += '.wav'
    pos, num_digits = None, None
    pos = name.index('#')
    num_digits = name.count('#')

    def get_name(i):
        nonlocal name, pos
        return name[:pos] + str(i).zfill(num_digits) + name[pos + num_digits:]

    i = 0
    while True:
        if not isfile(get_name(i)):
            break
        i += 1

    return get_name(i)


def main():
    path = os.getcwd() + "/Precise/model"

    while True:
        line = sys.stdin.readline().rstrip()
        if (line == "wake"):
            nameTemplate = "WakeWord#"
            os.chdir(path + "/wake-word")
        elif (line == "notwake"):
            nameTemplate = "NotWakeWord#"
            os.chdir(path + "/not-wake-word")
        else:
            continue

        p = pyaudio.PyAudio()
        d = record(p)
        currentName = nextName(nameTemplate)
        saveAudio(currentName, d)
        p.terminate()


if __name__ == '__main__':
    main()
