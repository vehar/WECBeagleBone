# Platform Support

The same image will run on BeagleBone White and Black.
All platform uniqueness handled at run time.
BeagleBone White tested with and without Beagleboardtoys DVI CAPE.
Automatic CAPE detection included (more CAPE support planned).

# Booting from a uSD card

To boot from a uSD card make sure the card is properly prepared and formatted.
Directly formatting the card from a Windows based PC is not enough as the card's boot partition will not be marked as "active", which is required for the AM335x processor to recognize the card. The best way to format is to use the HP USB based reader format tool (included in the tools directory) or use the TI format tool. 

## Using HP format tool
Insert the uSD card into a USB reader and plug in the PC. Execute the \DriveKey\HPUSBFW.exe program.
Select the correct drive and format. When complete, copy the MLO file (by itself) from the image folder to the root drive of the uSD card. Only after the MLO file is copied, copy the ebootsd.bin and NK.BIn file to the card. It is important the MLO file is copied by itself first as the MLO file must be the first entry in the FAT table of the card for proper booting.
Insert the card into the BeagleBone and power up. 

For BeagleBone Black insert card, press the user button and power up. Pressing the user button on power up will force a boot from the uSD card instead of the default eMMC device onboard. You can boot the CE image this way and still keep the factory Linux image in eMMC.

# Booting from eMMC
The exact same image files can be used to boot from eMMC if desired. 

_Note: Backup any of your Linux files/image files if needed although its a rather simple procedure to reflash the entire Linux image._
 
It is possible to repartition and format the eMMC under CE but this can be rather painful. I found the easiest way to proceed is leverage the existing Linux setup. To boot from the eMMC first prepare and boot from a uSD card as described above. Once booted, open the "BOOT" folder, this is the Linux "BEAGEBONE" partition. This partition is already formatted FAT32 and can be left as is. You can delete all the Linux files in this folder. Copy the MLO file from the "Storage Card" folder to the "BOOT" folder, after this file is copied proceed to copy the ebootsd.bin and NK.bin files also.
Remove the uSD card and reboot. Next, if CE starts go to Control Panel->Storage Manager. 
Select the DSKx: eMMC Disk. You should see two partitions listed: BEAGLEBONE and Part00.
Part00 is the Linux ext3 formatted partition and CE will not recognize it. With Storage manager you can delete Part00 and recreate it as a FAT32 or exFAT partition that CE can use as extra storage. Be sure to name the partition "Part00" as before.
After completing the above steps, reboot. With Windows Explorer you should see two disk type folders, BOOT and Hard Disk. BOOT is the smaller image file partition, it contains the boot files, image file and the persistent registry files. The Hard Disk folder is the large bulk data folder you can store your application data files in. 

# Partitioning eMMC
Unfortunately the factory FAT32 formatted boot partition may be too small for most Windows Embedded images so re-partitioning may be required.

I like having two partitions, one I’ll call the “BOOT” partition and this will hold the MLO, EBOOTSD.NB0 and NK.BIN files. It will also hold the hive based persistent registry files created after initial boot up. The second, larger partition will be the “Hard Disk” partition and is available for application use.

I created a “DISKPARTEMMC.EXE” partitioning tool and included it in the image to help with the partitioning and formatting tasks needed to properly configure the eMMC device for initial use. A simple batch file will kick off a script which will partition, format and copy the boot files to the eMMC memory. To use this tool it is very important to remember this batch file must ONLY be run when you have initially booted the device from a properly formatted uSD card (see above for uSD card creation).

Here is what happens:

# Create uSD card with all bootable files. 
# Place uSD card is BeagleBone’s uSD card cage. 
# Press user button and power on (pressing user button during power up forces boot from uSD card). 
# Open a command prompt. 
# Execute the PREPEMMC.BAT file in the \windows directory. 
PREPEMMC will:

# Prompt you to make sure you booted from uSD card. 
# Run the diskpartemmc executable with the partemmc.txt script file. 
The script will: 
# Clean the MBR deleting all existing partitions. 
# Create a primary partition of approximately 100Mb for the boot files. 
# Format the boot partition as FAT32. 
# Mark the boot partition as ACTIVE. 
# Create a second partition with all remaining space on the eMMC device. 
# Format the partition FAT32. 
The script will return and the batch will take over 
Batch file will copy MLO, EBOOTSD.NB0 and NK.BIN from the storage card to the boot partition. 
Remove the uSD card and cycle power. 
The BeagleBone should now boot directly from the eMMC device. 

A few things to note: The same image file set (MLO, EBOOTSD.NB0 and NK.BIN) works on the BeagleBone White and Black as executed from a uSD card or the BeagleBone Black executed from ether a 2Gb or 4Gb eMMC. Unlike other BSPs there is no need build separate images or keep track of several file sets based on which device you are booting from! 

