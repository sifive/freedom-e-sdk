#!/usr/bin/env python2.7
# Copyright 2019 SiFive, Inc #
# SPDX-License-Identifier: Apache-2.0 #
import argparse
import logging
import re


def parseRTLLog(rtlOut):

    test_ranges = [4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192,
                   16384, 32768, 65536, 131072, 262144, 524288]

    instns = []
    pat = re.compile('C[ ]*([0-9]+): [ ]+([0-9]+) \[([0-1])\] '
                     'pc=\[([0-9a-f]+)\] W\[r([0-9 ]+)=([0-9a-f]+)\].*'
                     ' R\[r([0-9 ]+)=([0-9a-f]+)\]'
                     ' R\[r([0-9 ]+)=([0-9a-f]+)\]'
                     ' inst=\[([0-9a-f]+)\] (.*)')
    with open(rtlOut) as fp:
        for line in fp:
            m = pat.match(line)
            if m:
                hart = int(m.group(1))
                cycle = int(m.group(2))
                isCommit = int(m.group(3))
                pc = m.group(4)
                rd = 'r'+str(int(m.group(5)))
                rdv = m.group(6)
                rs1 = 'r'+str(int(m.group(7)))
                rsv1 = m.group(8)
                rs2 = 'r'+str(int(m.group(9)))
                rsv2 = m.group(10)
                opcode = m.group(11)
                if isCommit == 1:
                    instn = {'hart': hart,
                             'cycle': cycle,
                             'pc': pc,
                             'opcode': opcode,
                             'rd': rd,
                             'rdv': rdv,
                             'rs1': rs1,
                             'rsv1': rsv1,
                             'rs2': rs2,
                             'rsv2': rsv2}
                    instns.append(instn)

    tests = []

    # Start analyzing
    test_idx = 0
    timestamps = []
    ld_num = 0
    for instn in instns:
        if (instn['opcode'] == '0020b033'):  # sltu zero,ra,sp
            timestamps.append(instn['cycle'])
            if len(timestamps) == 4:
                test = {}
                test['range'] = test_ranges[test_idx]
                test['cycle'] = timestamps[3] - timestamps[2]
                test['ld_num'] = ld_num
                test['ld_cycle'] = (float)(test['cycle']) / \
                    (float)(test['ld_num'])
                tests.append(test)
                del timestamps[:]
                ld_num = 0
                test_idx = test_idx + 1
        # Count lw s1,0(s1) and ld s1,0(s1)
        if (len(timestamps) == 3 and
                (instn['opcode'] == '00004084' or
                 instn['opcode'] == '0000639c' or
                 instn['opcode'] == '0007a783' or
                 instn['opcode'] == '0007b783' or
                 instn['opcode'] == '0000439c' or
                 instn['opcode'] == '00006318' or
                 instn['opcode'] == '00006084')):
            ld_num = ld_num + 1

    return tests


def printCSV(tests):
    print("range, total_cycle, ld_num, load_cycle")
    for test in tests:
        print("{}, {}, {}, {}".format(test['range'],
                                      test['cycle'],
                                      test['ld_num'],
                                      test['ld_cycle']))


def getPrettySize(kb):
    if kb < 1024:
        return str(kb) + ' KB'
    elif kb < 1024 * 1024:
        return str(kb/1024) + ' MB'
    elif kb < 1024 * 1024 * 1024:
        return str(kb/1024/1024) + ' GB'


def reportMemory(tests):
    # Calculate diff_rate
    for test_idx in range(0, len(tests)):
        if test_idx == 0:
            tests[test_idx]['diff_rate'] = 0
        else:
            tests[test_idx]['diff_rate'] = (tests[test_idx]['ld_cycle'] -
                                            tests[test_idx-1]['ld_cycle']) \
                / tests[test_idx-1]['ld_cycle']

    # Find the test where its next test has a big increasing ld_cycle
    mem_levels = []
    search_bump = False
    for test in tests:
        if abs(test['diff_rate']) >= 0.3:
            # bump found, push last test
            mem_levels.append(last_test)
            search_bump = False
        last_test = test

    if len(tests) > 0:
        mem_levels.append(tests[-1])
    # Report memory levels
    print("Memory level: {}".format(len(mem_levels)))
    for i in range(0, len(mem_levels)):
        if i == len(mem_levels) - 1:
            print("    Memory : "
                  "size: {}, "
                  "latency: {} cycles".format(
                      getPrettySize(mem_levels[i]['range']),
                      round(mem_levels[i]['ld_cycle'], 2)))
        else:
            print("    Level-{}: "
                  "size: {}, "
                  "latency: {} cycles".format(i+1,
                                              getPrettySize(
                                                  mem_levels[i]['range']),
                                              round(mem_levels[i]['ld_cycle'], 2)))


def analyze(rtlOut, detail=False):
    tests = parseRTLLog(rtlOut)
    if detail:
        printCSV(tests)
    reportMemory(tests)


def main():
    parser = argparse.ArgumentParser(
        description='Deduce cache size from analyzing RTLsim output.')
    parser.add_argument('--rtlOut', dest='rtlOut', required=True,
                        help='The RTLsim output file')
    parser.add_argument('--detail', dest='detail', action='store_true',
                        required=False, help='Detail output for judgement')
    args = parser.parse_args()

    analyze(args.rtlOut, args.detail)


if __name__ == "__main__":
    main()
