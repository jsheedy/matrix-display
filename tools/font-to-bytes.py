from fontTools import ttLib

tt = ttLib.TTFont('assets/PressStart2P-Regular.ttf')
print([n.string.decode('utf-8') for n in tt['name'].names])
# ??
