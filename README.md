There are a handful of applications for Markov chains, but the most common is text generation
(for example, the autocomplete text on your phone’s keyboard). The output text is based on a set
of training data, which is based on the probability of which words follow other words in the
training text. Those probabilities are used to generate a corpus, which is a probabilistic model
that we’ve calculated based on that source text. Once that corpus is generated, we represent it
as a graph and generate text from the path of our traversal. 
