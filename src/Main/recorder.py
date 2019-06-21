#!/usr/bin/env python3

import time

def main():
    print("begin")
    counter = 0
    while True:
        counter += 1
        time.sleep(2)
        print("In while")
        if counter == 6:
            break
    print("end")


if __name__ == '__main__':
    main()
