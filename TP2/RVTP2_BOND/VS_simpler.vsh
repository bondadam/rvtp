##############################################
##  Réalité  Virtuelle
##  Polytech 2019-2020
##
##  leo.donati@univ-cotedazur.fr
##
##  Tuto1
##
##############################################

attribute highp vec3 rv_Position;
uniform   highp mat4 u_ModelViewProjectionMatrix;
varying   highp vec4 outColor;
uniform   highp float u_opacity;
uniform   highp vec3 u_color;

void main(void)
{
    gl_Position = u_ModelViewProjectionMatrix * vec4(rv_Position,1);
    outColor = vec4(u_color, u_opacity);
}
