# Sound router

A sound router is a tool to route sound reproduction from a source to destinations.

A challenge requirement is just a base, but the futures requirement of a tool can growing.
An architecture of a developed to prevent bottlenecks of extending sub-commands or router features.

## Using

Commands declared as command line options and for making simpler using of a tool added a position argument.

Example of using:

```bash
# Immediately calculate and show the sound output for a given input srcReference
./sounds-router calc --srcReference 12

# Store a given srcReference for later usage
./sounds-router store --srcReference 12 --file ./source.dat

# Load a srcReference that was previously stored, calculate and show the sound output
./sounds-router load --file ./source.dat
```   

## Implementation

An implementation separated into two parts:

- a helper for building the new command of a tool;
- a router workflow.

### Command line 

Implementation based on an experience of using Go library [Cobra](https://github.com/spf13/cobra).

### A router

A base idea to separate responsibility of components by SOLID rules.

Challenge requirements contains the following subjects:

- an audio source which linked devices and plays a sound them;
- storage;
- a command executor.

Each component are implementing exactly features but widely using interfaces and dependency injection
to reducing risks and resources (time, developers) for extending them.  

## Trade-off

1. **Logging**. The tool is a console utility with exact output.
   The future requirements can be extending information for showing and
   needs to replace all of std::cout lines of code.

2. **File locking**. Source reference stored into a file without any locking, etc. 
   It based on no requirements related use cases and reducing code base.
   It will implements in an easy way just changing a storage class.  

3. **Parameters list**. It is strict for only two parameters. The new command might have
  the new options and needs extending command::Params class of command::Arguments.