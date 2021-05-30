#! /usr/bin/python3
import sys,getopt


def csv_to_graphml(weighted=True,infile="graph.csv",outfile="graph.graphml") :

    if infile == "": 
        infile = "graph.csv"

    f = open(infile,'r')

    if outfile == "" : 
        outfile = "graph.graphml"

    o = open(outfile,'w')

    nodes = {}

    edges = {} 

    while True : 
        line = f.readline() 
        if len(line) == 0 : 
            break
        else : 
            line = line[0:-1]
            line = line.split(',')
            if len(line) < 4 :
                break
            source = line[0]
            dest = line[1]
            if not weighted  :
                #print("Did you mean to make the graph unweighted?")
                w = 1 
            if  weighted : 
               # print("Did you mean to make the graph weighted?")
                w = 10 - int(line[2])
            if source not in nodes :
                nodes[source] = '<node id="'+source+'" />'+'\n' 
            if dest not in nodes:
                nodes[dest] =  '<node id="'+dest+'" />'+'\n'

            edges[source+','+dest] = '<edge id="{0}" source="'.format(hash(source+dest)%50000)+source+'" target="'+dest+'" useWeight="true" isDirect="true" weight="'+str(w)+'"/>'+'\n' 
            
    
    beginning='''<?xml version="1.0" encoding="UTF-8"?>
    <graphml xmlns="http://graphml.graphdrawing.org/xmlns"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:schemaLocation="http://graphml.graphdrawing.org/xmlns
    http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd">'''

    graph='''<graph id="G" edgedefault="directed">'''
    

    o.write(beginning+'\n')

    o.write(graph+'\n')

    for node in nodes.values() : 
        o.write(node)
    for edge in edges.values() :
       o.write(edge)

    o.write("</graph>"+'\n')

    o.write("</graphml>"+'\n')


def main(argv): 

    if len(argv) == 0 : 
        print(" Use the -h flag for usage format")
        sys.exit(2)

    inputfile = ''
    outputfile= ''
    weighted = True

    try : 
        opts,args = getopt.getopt(argv,"hi:o:",["weighted="])

    except getopt.GetoptError: 
        print ('./convert.py -i <input_file> -o <output_file>' )
        sys.exit(2)

    for opt,arg in opts :

        if opt == '-h' :
            print ('./convert.py -i <input_file> -o <output_file>')
            print ("Default input and output filename values are graph.csv and graph.graphml")
            print("Set weighted=True to read weight data, or weighted=False to set all weights to 1")
            sys.exit()
        elif opt == '-i': 
            inputfile = arg 
        elif opt == '-o': 
            outputfile = arg
        elif opt == "--weighted": 
            if arg == "True": 
                weighted = True
            elif arg == "False" :
                weighted = False
            else : 
                weighted = True

    csv_to_graphml(weighted,inputfile,outputfile) 
    print (' Successfully converted csv file to  graphml file ')

if __name__ == "__main__" :
    main(sys.argv[1:])








