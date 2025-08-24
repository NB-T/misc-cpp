s = """https://youtu.be/GKezbjohvR8?t=844https://youtu.be/5j-P_tHGSKw?t=1355
https://youtu.be/l7-J16e0TMI?list=PLVWaFpMwtaGiBxi79IUqnqn67WF5g5PR4&t=953
https://youtu.be/n2FxpdfoNWk?list=PLVWaFpMwtaGiBxi79IUqnqn67WF5g5PR4&t=1648
https://youtu.be/PcctOL4Axk8?t=1345
https://youtu.be/WFmnZ0ngVis?list=PLVWaFpMwtaGiBxi79IUqnqn67WF5g5PR4&t=749https://youtu.be/Uit7i7zByrU?list=PLVWaFpMwtaGiBxi79IUqnqn67WF5g5PR4&t=683https://youtu.be/Uit7i7zByrU?list=PLVWaFpMwtaGiBxi79IUqnqn67WF5g5PR4&t=1961https://youtu.be/AS-BP8YbIAo?list=PLVWaFpMwtaGiBxi79IUqnqn67WF5g5PR4&t=2108
https://youtu.be/lwlmhKxPd7Q?list=PLVWaFpMwtaGiBxi79IUqnqn67WF5g5PR4&t=504https://youtu.be/PyI8Jc_3OA0?list=PLVWaFpMwtaGiBxi79IUqnqn67WF5g5PR4&t=1120https://youtu.be/eM82L0n3Q7A?list=PLVWaFpMwtaGiBxi79IUqnqn67WF5g5PR4&t=1759https://youtu.be/Du05lffVnUo?list=PLVWaFpMwtaGiBxi79IUqnqn67WF5g5PR4&t=737https://youtu.be/Du05lffVnUo?list=PLVWaFpMwtaGiBxi79IUqnqn67WF5g5PR4&t=1459
https://youtu.be/WVod3aAsEyE?list=PLVWaFpMwtaGiBxi79IUqnqn67WF5g5PR4&t=754https://youtu.be/eLVnWGP3KRg?list=PLVWaFpMwtaGiBxi79IUqnqn67WF5g5PR4&t=24https://youtu.be/1Nt0HVMv3b8?list=PLVWaFpMwtaGiBxi79IUqnqn67WF5g5PR4&t=661https://youtu.be/spyv1HZDS0U?list=PLVWaFpMwtaGiBxi79IUqnqn67WF5g5PR4&t=584https://youtu.be/-wREyJKttqQ?list=PLVWaFpMwtaGiBxi79IUqnqn67WF5g5PR4&t=561https://youtu.be/WjzfCROU1JU?t=876https://youtu.be/Ykzlf4bN7no?list=PLVWaFpMwtaGiBxi79IUqnqn67WF5g5PR4&t=536https://youtu.be/CkNlTgT7yfs?t=1172https://youtu.be/mCaKYhLRlQw?t=1678https://youtu.be/s--USdyP1eE?t=2794https://youtu.be/s--USdyP1eE?t=2972https://youtu.be/-PvcULj8aqU?t=275https://youtu.be/UX49cxfZ1xg?t=2342https://youtu.be/clRmN0Gozvk?t=295
https://youtu.be/oSk7i-NmPkw?t=2718 https://youtu.be/65-_GpJtfpQ?t=13https://youtu.be/DvfXHaVt0m4?t=2839
https://youtu.be/ZZvsaqGotuE?t=1072https://youtu.be/ZGfOyPFR7fE?t=1439https://youtu.be/h8pHMU22jdY?t=1065"""

# split before "https"
s = s.split("https://")
# remove empty strings and strip whitespace
s = [x.strip() for x in s if x.strip()]
# join with "https://" to restore the URLs
s = ["https://" + x for x in s]
# join
s = "\n".join(s)
# add numbers for each line
s = "\n".join(f"{i + 1}. {line}" for i, line in enumerate(s.split("\n")))
print(s)