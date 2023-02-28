song = None
partiture = ''
with open('song.txt','r') as f:
    song = f.readlines()

for note in song:
    option = note.split('(')[0]
    num = None
    if option == 'delay':
        num = note.split('delay(')[1].split(')')[0]
    elif option == 'tone':
        num = note.split('tone(buzzer, ')[1].split(')')[0]
    else:
        num = 0
    partiture += f'{num},'
print(partiture)
print(len(song))    
    