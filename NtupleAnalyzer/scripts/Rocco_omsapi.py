import os
import sys
import json

from omsapi import OMSAPI



#fill your values
my_app_id='cms-l1scout-analysis'
my_app_secret='310Z6dQW39l3CllRc4YGAIM89bToEPoP'
omsapi = OMSAPI("https://cmsoms.cern.ch/agg/api", "v1", cert_verify=False)
omsapi.auth_oidc(my_app_id,my_app_secret)

"""
#Create a query.
query = omsapi.query("lumisections")
query.per_page = 10000  # to get all names in one go

query.attrs(["delivered_lumi"])
# Filter run
query.filter("run_number", run_number)


resp = query.data()
oms = resp.json()   # all the data returned by OMS
data = oms['data']
print(data)
"""

runs = [
    383812
    # 383331,383326,383323,383327,383277,383276,383275,383254,383255,383174,383173,383162,
    # 383155,383153,383034,382937,382924,382922,382921,382913,382878,382856,382834,382811,382810,382799,382795,382792,382791,382770,382769,382752,382750,
]

delivered_lumi = {}

irun = int(sys.argv[1])
frun = int(sys.argv[2])

for run in range(irun,frun):
    q = omsapi.query("runs").filter("run_number", run)
    # Chain filters
    q.paginate(page=1, per_page=1).sort("run_number", asc=False)

    # Execute query & fetch data
    response = q.data()

    # get delivered lumiDisplay JSON data
    # print(response.json()["data"][0]["attributes"]["delivered_lumi"])
    delivered_lumi[run] = response.json()["data"][0]["attributes"]["delivered_lumi"]

    print(delivered_lumi[run])

# print(delivered_lumi)
# print("Total:", sum(list(delivered_lumi.values())))
