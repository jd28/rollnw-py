import rollnw
from rollnw import Encounter
import json
import pytest


def test_encounter_default_construct():
    obj = Encounter()
    assert obj.handle().type == rollnw.ObjectType.encounter


def test_encounter_gff_construct():
    obj = Encounter.from_file(
        "tests/test_data/user/development/boundelementallo.ute")
    assert obj.common.resref == "boundelementallo"
