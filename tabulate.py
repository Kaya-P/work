import csv
with open('output.txt', 'r') as f:
    lines = [line.rstrip() for line in f]
    rows = []
    # each row has six data points
    # the six fields
    fields = ['Impressions', 'Total Engagements', 'Likes',
              'Profile Clicks', 'Retweets', 'Detail Expands']
    count = 0
    x = []
    for l in lines:
        print(l.isdigit())
        if(l.isdigit() == True):
            count += 1
            x.append(l)
            print(count)
            print(x)
            if (count % 6 == 0):
                rows.append(x)
                x = []
    print(rows)
    tablefile = "twitter_analytics.csv"
    # write to file
    with open(tablefile, "w") as csvfile:
        csvwriter = csv.writer(csvfile)
        csvwriter.writerow(fields)
        csvwriter.writerows(rows)
