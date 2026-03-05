import re

htt_pattern = '(CAG|CAA){18,}'
htt_mRNA = open('C:/Users/apsciuser/Downloads/htt_gene.fasta').read()
match = re.findall(htt_pattern, htt_mRNA)
print("Liczba polyQ wynosi:  " + str(len(match)))


