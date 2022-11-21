# Contributing

## Table of contents

- [Introduction](#introduction)
- [How to contribute](#how-to-contribute)
- [How to raise an issue](#how-to-raise-an-issue)
- [Feature request](#feature-request)

## Introduction

Thank you very much for being here! First of all, I want to let you know that contributions are more than welcome and really appreciated. In case you want to contribute, even with a small bug fix, you will be featured into the [credits list](https://github.com/JustWhit3/ptc-print#:~:text=Gianluca%20Bianco-,Other%20contributors,-Empty%20for%20the).

## How to contribute

To add your contribution, please follow these guidelines:

1) Fork your own copy of the repository.
2) Work on your changes / improvements in the forked repo.
3) **Test** if your changes / improvements are correctly implemented and all the other features are not compromised. See [here](https://github.com/JustWhit3/ptc-print#tests):
4) Run [execution benchmarks](https://github.com/JustWhit3/ptc-print#benchmarking) and [compilation benchmarks](https://github.com/JustWhit3/ptc-print#benchmarking-the-compilation-time) in order to be sure performance is not lost:
5) Before submitting the code, reformat it using the [`.clang-format`](https://github.com/JustWhit3/ptc-print/blob/main/.clang-format.md) file:

```bash
.clang-format -i /path/to/file
```

5) Optional, but really appreciated: update the [documentation](https://justwhit3.github.io/ptc-print/) (directly while writing the code) and the main [README](https://github.com/JustWhit3/ptc-print/blob/main/README.md) with the new features you added.
7) Finally, make the pull request.

Once your pull request will be submitted, I will carefully review it and, if it will be considered as an improvement, I will confirm it.

## How to raise an issue

If you find any bug or something you think doesn't work correctly in the code, you are free to open an issue, but before carefully read this passages:

1) If this issue is due to download, compilation or installation of the library, be sure to have read the [installation part](https://github.com/JustWhit3/ptc-print#install-and-use:~:text=setFlush(%20true%20)%3B-,Install%20and%20use,-Steps%3A) in the main README in which all the passages are explained in detail.
2) If this issue is due to a code feature, be sure to have run all the [tests](https://github.com/JustWhit3/ptc-print#install-and-use:~:text=cpp%0A./a.out-,Tests,-Different%20tests%20are) before, in order to see if your machine has all the necessary prerequisites installed.

Use [this](https://github.com/JustWhit3/ptc-print/blob/main/.github/ISSUE_TEMPLATE/bug_report.md) template to open the issue.

Once the issue is received, I will analyze it and once is solved I will respond asking confirmation about my fixing. In this case, if any answer is received in 7 days, the issue will be automatically closed.

## Feature request

To request a specific feature, open an issue and use [this](https://github.com/JustWhit3/ptc-print/blob/main/.github/ISSUE_TEMPLATE/feature_request.md) template.
