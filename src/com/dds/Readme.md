This document describes the ROS2 DDS Layer for FORTE.

This module relies heavily on code generation of two particular tools. Firstly, rosidl, in which .msg, .srv, and .action files can be read and .idl files will be generated. With these .idl files, a second generation, namely fastddsgen, generates .cxx files for the types and DDS implementation. These files are not included in the FORTE source tree, due to licensing conditions.

You can use any IEC61499 datatype and map them to corresponding ROS2 defined datatypes (which in fact map to c datatypes). The typical workflow is as follows:

  1.  We are able to map custom data types defined in 4diac to corresponding ROS2 datatypes. This is achieved by using the rosidl compiler and the fastdds tool fastddsgen.
  2.  Define a custom data type in 4diac and export it to .cpp files. It is important to wrap your data type in the form of an IEC61499 struct. For example, the example_message/StringDebug data type is an 
        IEC61499 struct with only one field, namely data, which is an IEC61499 STRING.
  3.  Define a .msg and convert it to an .idl file using rosidl.
  4.  Convert the .idl file to .cpp files using the fastddsgen tool (use version 2.5.x for conversion, as I have only tested this version: https://github.com/eProsima/Fast-DDS-Gen/tree/2.5.x).
  5.  Create a <Type>PubSub .cpp implementation for the new data type (refer to existing files).
  6.  Register the newly created <Type>PubSub into the DDS layer (refer to the ddspubsub.cpp file).
  7.  Use the newly created data type in the PUB or SUB FBs.
