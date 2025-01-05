#!/bin/sh

echo '"id","created_at","name","has_test","alternate_url"' > hh.csv
#curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
#brew install jq
jq -r -f filter.jq ../ex00/hh.json >> hh.csv