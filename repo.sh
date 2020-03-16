#!/bin/bash
set -e
curl -Lo .git/hooks/commit-msg http://10.10.10.218:8081/tools/hooks/commit-msg
chmod a+x .git/hooks/commit-msg
git config remote.origin.push refs/heads/*:refs/for/*
