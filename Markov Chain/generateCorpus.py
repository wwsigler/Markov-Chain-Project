import string

def makepairs(wordlist):
	lst = []
	for i in range(len(wordlist)-1):
		lst.append(tuple((wordlist[i], wordlist[i+1])))
	return lst

infile = open(input("enter filename "), "r")
#infile = open("pirates.txt", "r")

corpus = {}		#use a dictionary of dictionaries to store our corpus data
words = makepairs(infile.read().translate(str.maketrans('', '', string.punctuation)).split())	#read in our training data, removing punctuation.

#this loop counts the number of times word B follows word A
	#every pair of words is counted as a tuple (pair) and the value of dictionary at (a,b) is incremented
for word in words:
	if word[0] in corpus:
		corpus[word[0]][word[1]] = corpus[word[0]].get(word[1], 0) + 1
	else:
		corpus[word[0]] = {word[1] : 1}

infile.close()

#this is the part where we go through every value in the corpus and translate number of occurrences to a probability out of 1
for words in corpus:
	counter = 0
	for word in corpus[words]:
		counter += corpus[words][word]
	for word in corpus[words]:
		corpus[words][word] = corpus[words][word] / counter
		
outfile = open("corpus.txt", "w")

#lastly we format the output in a way that isn't a pain in the ass for c++ to parse (jk, it's always a pain in the ass to parse file input in c++)
outfile.write(str(len(corpus)))
for words in corpus:
	outfile.write('\n' + words)
	for word in corpus[words]:
		outfile.write(',' + word + ' ' + str(corpus[words][word]))

outfile.close()
