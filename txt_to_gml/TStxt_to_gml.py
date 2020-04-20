import sys

if len(sys.argv)<2 or len(sys.argv)>2:
  exit()

input_file_name = sys.argv[1]


f = open(input_file_name, "r")

output_gml = "graph\n[\tdirected\t1\n"

#nodes
firstline = f.readline()
isNodeList = "Node:" in firstline

if isNodeList:
  while True:
    line = f.readline()

    print(line)

    if line=="" or line == "\n" :
      break;
    
    linearray = line.split(",")
    output_gml+="\tnode\n\t[\n\t\tid\t"+linearray[0]+"\n\t]\n"

#edges
  firstline = f.readline()
  isNodeList = "Edge:" in firstline
  while True:
    line = f.readline()

    print(line)

    if line=="" or line == "\n" :
      break;
    
    linearray = line.split(",")
    output_gml+="\tedge\n\t[\n\t\tsource\t"+linearray[1]+"\n\t\ttarget\t"+linearray[2]+"\n\t]\n"

f.close();
output_gml+="]"
print(output_gml)

f = open(input_file_name+".gml", "a")
f.write(output_gml)
f.close()
