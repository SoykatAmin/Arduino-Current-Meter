# Arduino-Current-Meter
A current meter. Divided by two parts, PC and Arduino. Arduino will store statistics. On request, it will send data to PC. 
PC have an interface that allows to send requests to arduino:
- Online-Mode: Arduino sends current samples to PC at x rate without storing.
- Offline-Mode: Arduino stops sending current samples to PC (Offline is default mode).
- Query Statistics: Arduino sends all statistics to PC, PC saves it.
- Clear Statistics: Arduino clear all statistics.
- Print Statistics: Print statistics saved in PC.