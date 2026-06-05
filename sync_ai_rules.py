#!/usr/bin/env python3
import yaml, os, json
from pathlib import Path
def main():
    cfg = yaml.safe_load(open("ai_project.yaml"))
    proj_name = cfg["project"]["name"]
    with open(".cursorrules", "w") as f:
        f.write(f"Project: {proj_name}\n")
        for rule in cfg["coding_rules"]:
            f.write(f"- {rule}\n")
        f.write(f"Do NOT modify: {', '.join(cfg['locked_files'])}\n")
    os.makedirs(".continue", exist_ok=True)
    with open(".continue/rules.md", "w") as f:
        for rule in cfg["coding_rules"]:
            f.write(f"- {rule}\n")
    os.makedirs(".github", exist_ok=True)
    with open(".github/copilot-instructions.md", "w") as f:
        for rule in cfg["coding_rules"]:
            f.write(f"- {rule}\n")
    with open("CODEX.md", "w") as f:
        f.write(f"# CODEX.md - {proj_name}\n\n## Coding Rules\n")
        for rule in cfg["coding_rules"]:
            f.write(f"- {rule}\n")
        f.write("\n## Locked Files\n")
        for l in cfg["locked_files"]:
            f.write(f"- {l}\n")
    print("All AI rule files synced.")
if __name__ == "__main__":
    main()
