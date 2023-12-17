# A Turing machine simulator made in C++.

## Quick start
Clone the repository and create a config file for the transition function $\delta$ of your desired Turing machine.
The transitions are of the form:

```
<current state> <read symbol> <write symbol> <direction next state>
```
The config file also needs an initial state, written like this:

```
_initial_state_ <initial state>
```

So, the whole config file for a Turing machine which replaces 1s with 0s and vice versa could look like this:

```
_initial_state_ s0
s0 1 0 R s0
s0 0 1 R s0
```
If a state is prefixed by `halt`, it will make the machine halt when it transitions to that state. For example:

```
s0 1 1 R halt-accept
s0 0 0 R halt-reject
```

When the config is written you can run:

```zsh
make
./turing <config file> <input string>
```

This will run the Turing machine and display information about the state it is in. It might look something like this:

```
State=s4, Symbol=1, Transition=1 L s4
Tape X11̲̲1̲̲0X110
```

