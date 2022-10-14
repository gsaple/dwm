# dwm
My built of the suckless [dynamic window manager](https://dwm.suckless.org).<br />
Massive shout-out to Bakkeby's [repo](https://github.com/bakkeby/dwm-commented) for the great documentation of this elegant software.

https://user-images.githubusercontent.com/108666441/195844889-2adc4385-bfbd-4165-af44-2cdb6bc85db0.mp4

## Community Patches
Following patches are taken from the [dwm patch website](https://dwm.suckless.org/patches/) and applied directly to my build.
- [attachaside](https://dwm.suckless.org/patches/attachaside/dwm-attachaside-6.3.diff): makes new clients get attached and focused in the stacking area instead of always becoming the new master.
- [fixborders](https://dwm.suckless.org/patches/alpha/dwm-fixborders-6.2.diff): makes only borders opaque.
- [focusonclick](https://dwm.suckless.org/patches/focusonclick/dwm-focusonclick-20200110-61bb8b2.diff): switches focus only by mouse click and not sloppy.
- [killunsel](https://dwm.suckless.org/patches/killunsel/dwm-killunsel-ceac8c91ff.diff): kills all visible clients that are unselected.
- [layoutscroll](https://dwm.suckless.org/patches/layoutscroll/dwm-layoutscroll-6.2.diff): cycles through all layouts defined in layouts array.
- [noborder](https://dwm.suckless.org/patches/noborder/dwm-noborderselflickerfix-2022042627-d93ff48803f0.diff): removes the border when there is only one window visible.
- [notitle](https://dwm.suckless.org/patches/notitle/dwm-notitle-20210715-138b405.diff): does not show the title of a client.
- [shiftview](https://lists.suckless.org/dev/1104/7590.html):shifts the tagset left/right 
- [pertag](https://dwm.suckless.org/patches/pertag/dwm-pertag-20200914-61bb8b2.diff): keeps layout, mwfact, barpos and nmaster per tag.
- [togglefullscreen](https://github.com/bakkeby/patches/blob/master/dwm/dwm-togglefullscreen-6.3.diff): toggles fullscreen for the focused client window.
- [vanitygaps](https://dwm.suckless.org/patches/vanitygaps/dwm-vanitygaps-20190508-6.2.diff): adds (inner) gaps between client windows and (outer) gaps between windows and the screen edge in a flexible manner.
- [Xresources](https://dwm.suckless.org/patches/xresources/dwm-xresources-20210827-138b405.diff): allows to handle settings from Xresources.

## My Patches
Following patches are inspired by the community patches. I ended up with my own implementation because I want to bloat it in my own way.
