# Sim-emulator
Programmatic simcard open source emulator.  

## Dependencies
Make, gcc, Python

## Current state
* Currently only at initial stage with no functional
* Basic system for building simcard filesystem is implemented

## Configuring filesystem of simcard emulator
- To add a file just add it to where it belongs relative to MF directory
- For dedicated files (DF) additional files with information supplied, see .desc files under MF for each dedicated file
- For entry files (EF) format is as follows:
    - First line: TRN or LIN - transparent of linear EF
    - Second line: fid in hex starting with 0x
    - Third line: Short fid (sfid), hex
    - Fourth line: Description text
    - Fifth line: Record max length for linear EF
    - Sixth line: File size for transparent EF, for linear file it is calculated during parsing
    - Seventh line: Data in hex each two symob for a byte for transparent EF
    - For linear EF Seventh and further lines each represent data for subsequent records

At the moment most of the data in files is copied from *Pysim* project just for reference, and probably needs to be edited in the future

```
make
```
will first check if MF directory has changed. If changed, *translatefs.py* is launched, which generates **fs.inc** file. It contains macros sequence which is understood by gcc at the step of building project

## TODO
* Add apdu command handling
* Add GSM authentication algorythm
