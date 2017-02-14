# MacLLC

MAC Address ORG/LLC Auto-Detection

Dragging the result file of "arp -a" to the MacLLC.exe,You will find the Organization(LLC).

Windows 7 & VS2013 & QT 5.7 Static

----------------------------------

Example:


C:\Users\Gaearrow>arp -a >arp.txt

C:\Users\Gaearrow>MacLLC.exe arp.txt

Oui Version =  Generated: Tue, 14 Feb 2017 11:20:05



Success Add LLC to [C:/Users/Gaearrow/arp.txt-llc.txt]


[arp.txt]

Interface: 192.168.102.135 --- 0xe
  
Internet Address      Physical Address      Type
  
192.168.102.2         00-50-56-f3-b8-2d     dynamic
  
192.168.102.3         90-7F-61-c3-b8-2d     dynamic
  
192.168.102.4         9C-8E-99-00-00-16     dynamic
  
192.168.102.5         00-F8-71-00-00-fc     dynamic
  
239.255.255.250       01-00-5e-7f-ff-fa     static
  
255.255.255.255       ff-ff-ff-ff-ff-ff     static



[arp.txt-llc.txt]

Interface: 192.168.102.135 --- 0xe
  
Internet Address      Physical Address      Type             LLC
  
192.168.102.2         00-50-56-f3-b8-2d     dynamic        VMware, Inc.
  
192.168.102.3         90-7F-61-c3-b8-2d     dynamic        Chicony Electronics Co., Ltd.
  
192.168.102.4         9C-8E-99-00-00-16     dynamic        Hewlett Packard
  
192.168.102.5         00-F8-71-00-00-fc     dynamic        DGS Denmark A/S
  
239.255.255.250       01-00-5e-7f-ff-fa     static         Not Found
  
255.255.255.255       ff-ff-ff-ff-ff-ff     static         Not Found
