#!/bin/bash - 
#===============================================================================
#
#          FILE:  wd.sh
# 
#         USAGE:  ./wd.sh 
# 
#   DESCRIPTION:  
# 
#       OPTIONS:  ---
#  REQUIREMENTS:  ---
#          BUGS:  ---
#         NOTES:  ---
#        AUTHOR: YOUR NAME (), 
#       COMPANY: 
#       CREATED: 2012年01月30日 12时59分21秒 CST
#      REVISION:  ---
#===============================================================================

set -o nounset                              # Treat unset variables as an error

	sudo losetup -o 1048576 /dev/loop0  ../hd.img
	sudo mount /dev/loop0 ../hd

