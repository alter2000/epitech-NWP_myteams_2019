{ pkgs ? import <nixpkgs> {} }:

with pkgs;

{
  env = stdenv.mkDerivation {
    name = "c-project";
    buildInputs = [ pkg-config libuuid ];
    propagatedBuildInputs = [ pkg-config libuuid ];
    nativeBuildInputs = [ pkg-config libuuid ];
  };
}
