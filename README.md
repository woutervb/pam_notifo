pam\_notifo
==========
 
This project (based on work from Robert Harder; http://iharder.sourceforge.net/current/macosx/pam_notifo/), which will allow the pam system to send notifications via the Notifo service.
 
To use this module one needs to create a 'service' at notifo, and use the service name and key below. After that, the notif\_to paramete has to point to a 'notifo' account that is (or will be) subscribed to the service.
 
Configuration
=============
Edit the pam configuration file of the service you with to receive notifications from, using your favorite editor and add a line like the one below:

    session    optional       pam_notifo.so notifo_user=johndoe notifo_api_key=062c10a7b43cb9b6634dfdc20b37e070 notifo_to=user
 
Building & Installing
=====================
Simply checkout this project from git and run make.
 
To install run make install
 
TODO
====
* Implement error checking on missing / wrong parameters and function call failure
* Better testing on other platforms then ubuntu 12.04
  
License
=======
Copyright (C) \<2012\> \<copyright Wouter van Bommel\>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
