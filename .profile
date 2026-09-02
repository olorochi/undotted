export MAKEFLAGS="-j 12"
export SAMUFLAGS="-j 12"
export COMMON_FLAGS="-O2 -pipe -march=native"
export CFLAGS="$COMMON_FLAGS"
export CXXFLAGS="$COMMON_FLAGS"
export FCFLAGS="$COMMON_FLAGS"
export FFLAGS="$COMMON_FLAGS"
export RUSTFLAGS="$RUSTFLAGS -C target-cpu=native"

export HOSTNAME=$(cat /proc/sys/kernel/hostname)
export PATH=~/scripts:$PATH

export EDITOR=vim
export PAGER="vim -R -"
export MANPAGER="vim -M +MANPAGER"

export XDG_RUNTIME_DIR=/tmp/$(id -u)-runtime-dir
if ! test -d "${XDG_RUNTIME_DIR}"; then
    mkdir "${XDG_RUNTIME_DIR}"
    chmod 0700 "${XDG_RUNTIME_DIR}"
fi

export HISTFILE=~/.cache/histfile
export HISTSIZE=10000
export SAVEHIST=100000

export ENV=$HOME/config/kshrc
export XDG_CONFIG_HOME=~/config

[[ $(tty) = "/dev/tty1" ]] && exec dbus-launch sway # !! EXEC !!
return 0
