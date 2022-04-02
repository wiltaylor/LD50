{ pkgs ? <nixpkgs> }:
let

  tmuxIde = pkgs.writeScriptBin "tmuxide" ''
    tmux new-session -d -s game vim
    tmux rename-window 'neovim'
    tmux select-window -t 'game:0'
    tmux split-window -v -p 30 zsh
    tmux attach-session -tgame
  '';
in pkgs.mkShell {
  name = "gamedev";
  buildInputs = with pkgs; [
    gcc
    gnumake
    raylib
    tmuxIde
  ];

  shellHook = ''
    echo "Game Dev Shell"
    export SHELL=zsh
    export EDITOR=vim
  '';
}
