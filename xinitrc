#!/bin/sh

hsetroot -solid "#6c6c6c" &
slstatus &
dunst &			# dunst for notifications
xset r rate 300 50 &	# Speed xrate up
compton &

# Set Caps to Mod/Escape
setxkbmap -option caps:super && killall xcape 2>/dev/null ; xcape -e 'Super_L=Escape' &
# Properties button extra Mod/Escape
xmodmap -e 'keycode 135 = Super_R' &
