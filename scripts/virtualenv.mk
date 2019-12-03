
venv/bin/activate: requirements.txt
	python3 -m venv venv
	. $@ && pip install --upgrade pip
	. $@ && pip install -r $<

.PHONY: clean-virtualenv
clean-virtualenv:
	-rm -rf venv

