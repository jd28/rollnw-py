import nox
import os
import sys


@nox.session(venv_backend="none")
def dev(session: nox.Session) -> None:
    """
    Prepare a .venv folder if needed, then install dependencies.
    """
    if not os.path.isdir(".venv"):
        session.run(sys.executable, "-m", "venv", ".venv")

    pip = ".venv/bin/pip" if os.name != "nt" else ".venv\\Scripts\\pip.exe"

    session.run(pip, "install", "scikit-build-core[pyproject]")
    session.run(
        pip,
        "install",
        "--no-build-isolation",
        "--check-build-dependencies",
        "-ve.",
        "-Cbuild-dir=build",
    )


@nox.session(venv_backend="none")
def build(session: nox.Session) -> None:
    session.run(
        "pip",
        "install",
        "-ve.",
        "--no-build-isolation",
        "-Cbuild-dir=build",
    )
