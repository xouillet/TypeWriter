#! /usr/bin/env python3

import argparse
import serial
import sys
import tty
import textwrap
import io
import unicodedata

TYPEWRITER_SHORTCUT = {
    "A": (18, "Set left margin"),
    "E": (19, "Set right margin"),
    "P": (12, "Page feed"),
    "L": (17, "Set auto line feed"),
    "B": (14, "Bold"),
    "U": (6, "Underline"),
}


def typewriter(ser):
    print("Typewriter mode")
    print("Shortcuts:")
    for key, (_, desc) in TYPEWRITER_SHORTCUT.items():
        print(f" * CTRL-{key}: {desc}")
    print()
    mode = tty.tcgetattr(0)
    tty.setraw(sys.stdin)
    while True:
        char = sys.stdin.read(1)
        code = ord(char)
        if code == 3:
            break
        elif chr(code + 64) in TYPEWRITER_SHORTCUT:
            code, desc = TYPEWRITER_SHORTCUT[chr(code + 64)]
            char = chr(code)
            print(f"> {desc}\r")
        elif code < 32 and code != 13:
            continue  # non-printable
        ser.write(char.encode("latin1"))
        wait_ready(ser)

    tty.tcsetattr(0, tty.TCSAFLUSH, mode)


def wait_ready(ser):
    while True:
        read = ser.read()
        if read == b"." or read == b"":
            break


def main():
    parser = argparse.ArgumentParser(description="Print on Panasonic R191")
    parser.add_argument("--port", metavar="port", type=str, help="COM port", default="/dev/ttyACM0")
    parser.add_argument("file", metavar="file", type=str, help="File name", default=None, nargs="?")
    parser.add_argument(
        "--no-newline", help="Don't print a new line before printing", action="store_true"
    )

    args = parser.parse_args()
    with serial.Serial(args.port, 9600) as ser:
        ser.timeout = 1
        wait_ready(ser)
        ser.timeout = 60
        if args.file is None and sys.stdin.isatty():
            typewriter(ser)
        else:
            with open(args.file, "r") if args.file else sys.stdin as f:
                lines = f.readlines()
            content = ""
            for line in lines:
                for wrapline in textwrap.wrap(line, 70):
                    content += wrapline + "\n"
            content = unicodedata.normalize("NFC", content).encode("latin1", "ignore")
            content = io.BytesIO(content)

            if not args.no_newline:
                ser.write(b"\n")
            while True:
                buf = content.read(60)
                if buf == b"":
                    break
                ser.write(buf)
                wait_ready(ser)


if __name__ == "__main__":
    main()
