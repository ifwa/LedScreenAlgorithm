## Led Screen Algorithm

---

### About

This is a simple LED screen display algorithm. It was originally used in a micro-controller (EFM32) with an LED display panel. Although this project was not in mass production for commercial reasons, the algorithm had been tested to be reliable. To abstract the algorithm, I took out the hardware-related part, added a simulator which can let us see the effect on the computer.

This algorithm implements many effects, such as laser, snow, left moving, right moving, up moving, down moving, scroll, marquee ... and so on. It uses a refresh rate of 25 frames per second to display the effect and it also supports 4-level brightness adjustment. The brightness adjustment is not done by the analog circuit, but by increasing the refresh rate by 4 times, which means the real refresh rate is 100 frames per second.

### How to Run

To demonstrate the effect, we can run it on the terminal of Unix/Linux/macOS.

Before we run it, we should install the 'ncurses' library.

For example, type this on the terminal of Ubuntu (or other Debian Linux).
```
$ sudo apt-get install libncurses5-dev
```

Or, type this on the terminal of macOS.
```
$ sudo brew install ncurses
```

After the installation of 'ncurses', type this to build the project.

(The project has already been built in macOS, so macOS users can try to skip this step.)
```
$ make clean$ make
```

And then, type this to run.
```
$ ./ledsim
```

This demonstration shows some Chinese characters. "暴走漫画" means "Rage Comic". "美国队长" means "Captain America". "动物森林" means "Animal forest". They are just some words that first came to my mind.

---
