# CIE Tools


## Convert Formats: RGB/XYZ/LAB/LCH
```py
import cietools

rgb = (150, 24, 51)
xyz = cietools.rgb2xyz(rgb)
lab = cietools.rgb2lab(rgb)
lch = cietools.rgb2lch(rgb)

...
lch_from_xyz = cietools.xyz2lch(xyz)
rgb_from_lch = cietools.lch2rgb(lch)
```

## Calculate Delta E 76/94/CMC/2000
```py
import cietools

lab1 = (43.54, 54.58, 22.87)
lab2 = (43.54, 60.58, 87.87)

delta_76 = cietools.deltaE76(lab1, lab2)
delta_94 = cietools.deltaE94(lab1, lab2)
delta_cmc = cietools.deltaE_CMC(lab1, lab2)
delta_2000 = cietools.deltaE2000(lab1, lab2)
```