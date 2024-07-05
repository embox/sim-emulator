This directory contains the core architecture for the esim inspired from the standard SGP.32-1.0-1 provided from GSMA, the link to the standard is 
https://www.gsma.com/solutions-and-impact/technologies/esim/wp-content/uploads/2023/05/SGP.32-1.0-1.pdf

Please refer to Section 2, on page 12/162 from above documentation to understand, there are two archiecture schemes possible. 

First scheme, which is implemented in this project, is with IPA (IoT Profile Assitant) on the IoT device. 
Second scheme, is another possibility in which IPA is on eUICC itself. 

Without any loss of generality, this project is built on first scheme, please also find image of first scheme in folder as well. 

For the connection between different units of architecture, there are interfaces, for detailed description please refer to 
Table 1: Inteferaces, on page 15 of standard SGP.32-1.0-1, or for quick glance, you may take look on image interfaces.png   

** Understsanding the architecture **

The structure of parent archiecture directory is shown below, this shows general structure of operation. Note it may change in future.

├── documentation
│   ├── architecture.png
│   ├── interfaces.png
│   └── readme.txt
├── eSimIoTRemoteManager.c
├── IoTDevice
│   ├── eUICC
│   │   ├── ISD-P.c
│   │   └── ISD-R.c
│   └── IPAd.c
├── Operator.c
├── SM-DPPlus.c
└── SM-DS.c

