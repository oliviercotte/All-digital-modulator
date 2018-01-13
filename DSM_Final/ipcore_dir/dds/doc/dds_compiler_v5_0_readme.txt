CHANGE LOG for Xilinx LogiCORE DDS Compiler 5.0

Release Date:  October 2, 2013 
--------------------------------------------------------------------------------

Table of Contents

1.   INTRODUCTION 
2.   DEVICE SUPPORT    
3.   NEW FEATURE HISTORY   
4.   RESOLVED ISSUES 
5.   KNOWN ISSUES & LIMITATIONS 
6.   TECHNICAL SUPPORT & FEEDBACK 
7.   CORE RELEASE HISTORY 
8.   LEGAL DISCLAIMER 

--------------------------------------------------------------------------------


1. INTRODUCTION

  This file contains the change log for all released versions of the Xilinx 
  LogiCORE IP DDS Compiler. 

  For the latest core updates, see the product page at:

    http://www.xilinx.com/products/ipcenter/DDS_Compiler.htm

  For installation instructions for this release, please go to:

    http://www.xilinx.com/ipcenter/coregen/ip_update_install_instructions.htm

  For system requirements:

    http://www.xilinx.com/ipcenter/coregen/ip_update_system_requirements.htm


2. DEVICE SUPPORT 

  2.1. ISE

    The following device families are supported by the core for this release:

    All Series 7 devices
    All Virtex-6 devices
    All Spartan-6 devices


3. NEW FEATURE HISTORY

  3.1 ISE
 
  v5.0
    - Ongoing new device support.
    - AXI4 Stream interfaces replace old pinout

  v4.0 
    - Note: DDS Compiler version 4.0 is not bit-accurate with respect to version 3.0
      and earlier. In particular, first order Taylor Series Correction table entries
      have been optimized to improve overall accuracy. Extended range of DDS with no
      noise shaping may reduce DATA width requirements. The update function will aim
      to adjust Frequency Resolution to maintain the phase width and associated DATA
      width.  Note that this may result in the specified Frequency Resolution parameter
      changing. However, as phase width is maintained, this will not affect
      the actual resolution of frequency or phase values. Also, there have been
      changes to latency, in particular to accommodate the new dynamic phase
      increment and phase offset options. Accumulator Latency has been removed
      and is assumed to be One.


4. RESOLVED ISSUES 

  4.1 ISE

    - N/A


5. KNOWN ISSUES & LIMITATIONS 

  The following are known issues for this core at time of release:

  5.1 ISE
    1. TLAST may be incorrectly asserted at power-up or after a reset for the following core configuration:
       Parts Present = DDS (both phase generator and SIN/COS LUT present)
       Channels = 2
       Phase Increment = Fixed
       Phase Offset = None or Fixed
       Output TLAST = Vector Framing
       - Workaround:
         Set M_DATA and/or M_PHASE TUSER setting to "Channel ID" or "User Field and Channel ID" (as appropriate). 
         The LSB of the TUSER output will be asserted to indicate the last (second) channel. 
         This bit may then be passed to downstream modules in place of the TLAST output.
       - CR 574542
       - AR 42351

    2. Any data input to the core in the clock cycle following the de-assertion will be dropped. 
       - Workaround is to ensure TVALID is not asserted to either input channel on the clock cycle immediately 
         following aresetn deassertion.
       - CR 593280
       - AR 40551 

    3. It is possible for the configuration channel in multichannel mode to lock up and deassert
       tready in the context of an ACLKEN signal with fixed mark/space ratio, e.g. 1 in 2 clock 
       cycles.
       - Workaround is either not to use ACLKEN, which is not recommended for AXI operation, or
         to use streaming mode input instead.
       - CR 653218

    4. The demonstration testbench may fail with syntax errors due to either an extraneous comma in the
       port map of the design under test or of a mismatch of ports to the design under test. 
       - Workaround is to hand edit the demonstration testbench.
       - CR 678866
       - AR 51915
        

  - For a comprehensive listing of Known Issues for this core, please see the IP 
    Release Notes Guide,  
    
    www.xilinx.com/support/documentation/user_guides/xtp025.pdf


6. TECHNICAL SUPPORT & FEEDBACK

  To obtain technical support, create a WebCase at www.xilinx.com/support.
  Questions are routed to a team with expertise using this product.
  Please feel free to leave feedback on this IP under the "Leave Feedback"
  menu item in Vivado/PlanAhead.

  Xilinx provides technical support for use of this product when used
  according to the guidelines described in the core documentation, and
  cannot guarantee timing, functionality, or support of this product for
  designs that do not follow specified guidelines.


7. CORE RELEASE HISTORY

Date        By            Version      Description
================================================================================
10/02/2013  Xilinx, Inc.  5.0          ISE 14.7 support and Production support for Series 7
06/19/2012  Xilinx, Inc.  5.0          ISE 14.6 support
03/20/2012  Xilinx, Inc.  5.0          ISE 14.5 support. 
12/18/2012  Xilinx, Inc.  5.0          ISE 14.4 and Vivado 2012.4 support
10/16/2012  Xilinx, Inc.  5.0          ISE 14.3 and Vivado 2012.3 support
07/25/2012  Xilinx, Inc.  5.0          ISE 14.2 and Vivado 2012.2 support
04/24/2012  Xilinx, Inc.  5.0          ISE 14.1 support
01/11/2012  Xilinx, Inc.  5.0          ISE 13.4 support
10/19/2011  Xilinx, Inc.  5.0          ISE 13.3 support
06/22/2011  Xilinx, Inc.  5.0          ISE 13.2 support, Artix-7 support
03/01/2011  Xilinx, Inc.  5.0          ISE 13.1 support, Virtex-7 and Kintex-7 support
09/21/2010  Xilinx, Inc.  5.0          ISE 12.3 support, AXI4-Stream interface
04/19/2010  Xilinx, Inc.  4.0          ISE 12.1, Virtex-6Q and Spartan-6Q support
12/02/2009  Xilinx, Inc.  4.0          Spartan-6 Lower Power device support and Automotive Spartan-6 support
09/16/2009  Xilinx, Inc.  4.0          Virtex-6 Lower Power device support
06/24/2009  Xilinx, Inc.  3.0          Virtex-6, Spartan-6 support
03/24/2008  Xilinx, Inc.  2.1          Bugfixes
05/17/2007  Xilinx, Inc.  2.0          Virtex-5 and Spartan-3ADSP support
11/30/2006  Xilinx, Inc.  1.1          Bugfixes
09/28/2006  Xilinx, Inc.  1.0          Initial release
================================================================================


8. LEGAL DISCLAIMER

  (c) Copyright 2010 - 2013 Xilinx, Inc. All rights reserved.
  
  This file contains confidential and proprietary information
  of Xilinx, Inc. and is protected under U.S. and
  international copyright and other intellectual property
  laws.
  
  DISCLAIMER
  This disclaimer is not a license and does not grant any
  rights to the materials distributed herewith. Except as
  otherwise provided in a valid license issued to you by
  Xilinx, and to the maximum extent permitted by applicable
  law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
  WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
  AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
  BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
  INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
  (2) Xilinx shall not be liable (whether in contract or tort,
  including negligence, or under any other theory of
  liability) for any loss or damage of any kind or nature
  related to, arising under or in connection with these
  materials, including for any direct, or any indirect,
  special, incidental, or consequential loss or damage
  (including loss of data, profits, goodwill, or any type of
  loss or damage suffered as a result of any action brought
  by a third party) even if such damage or loss was
  reasonably foreseeable or Xilinx had been advised of the
  possibility of the same.
  
  CRITICAL APPLICATIONS
  Xilinx products are not designed or intended to be fail-
  safe, or for use in any application requiring fail-safe
  performance, such as life-support or safety devices or
  systems, Class III medical devices, nuclear facilities,
  applications related to the deployment of airbags, or any
  other applications that could lead to death, personal
  injury, or severe property or environmental damage
  (individually and collectively, "Critical
  Applications"). Customer assumes the sole risk and
  liability of any use of Xilinx products in Critical
  Applications, subject only to applicable laws and
  regulations governing limitations on product liability.
  
  THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
  PART OF THIS FILE AT ALL TIMES.
  
