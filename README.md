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
Following patches are inspired by the community patches. I ended up with my own implementation simply because I want to bloat it in my own way.

### [clickable_icons](https://github.com/gsaple/dwm/blob/main/my_patches/clickable_icons.diff)
#### description
- draw a set of clickable icons (or texts) at where the title bar used to be.
- dwm `drawbar()` draws status bar first, tag bar second, title bar last. If there is not enough space left to draw _**all**_ icons, then _**no**_ icon will be drawn.
#### patch
- patch it ON TOP OF [notitle](https://dwm.suckless.org/patches/notitle/dwm-notitle-20210715-138b405.diff).
 
### [supreme_statusbar](https://github.com/gsaple/dwm/blob/main/my_patches/supreme_statusbar.diff)
#### description
- be able to customise the colour of the status bar WITHIN `config.def.h`.
- optional to cycle through 3 different styles of status bar: powerline, roundedcorner, xmonad(inspired by [DistroTube](https://www.youtube.com/c/DistroTube)'s Xmonad build).
- optional to shift colour to the right each time `drawbar()` is called, which is, to no one's suprise, absolutely useless.
- some notes related to rounded corner:
  - unlike the powerline style, no algorithm is used to rasterise a half-circle (while I tried and failed :sweat:).
  - instead, two nerd font half-circle glyphs are used to 'cheat' a rounded corner. As a result, two rectangles (up and down) are jagged out.
  - A workaround is to fill those two rectangles with background colour to 'clear' it, causing the roundedcorner-style-status-bar slightly shorter than the other two.
  - unfortunately the height of the aforementioned rectangles seems to be font-size dependent (usually is 3, but sometimes 2 is better).
#### patch
- nerdfont is needed.
- `stext` needs to be comma (`,`) seperated as the whole string will be splited using comma as a delimiter, e.g.
  ```
  xsetroot -name "$info4,$info3,$info2,$info1"
  ```
- this patch is NOT compatible with [status2d](https://dwm.suckless.org/patches/status2d/).
- all config variables are defined in `config.def.h` with a explanatory comment except for `jagged_pixel` which is roughly explained in the above notes.

### [colourful_tags](https://github.com/gsaple/dwm/blob/main/my_patches/colourful_tags.diff)
#### description
- different tags have colourful foregrounds, the same background, regardless of being viewed or not.
- the tag being viewed is distinguished by a different icon (or text) from its non-viewed counterparts.
#### patch
- nerdfont is needed

## TODO
document all the patches and submit some useful ones to the community.



