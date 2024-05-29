textinit = open("/Users/eugene/CPP files/template for pokemons raylib/assets/maps csv sources/generalMap_terrain2(mountains).csv", "r")

arr = []


for i in textinit:
    arr.append(i+",")

f = open("/Users/eugene/CPP files/template for pokemons raylib/assets/maps csv sources/terrain2(mountains).txt", "w")

for i in arr:
    f.write(i)