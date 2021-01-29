##############################################
##  Réalité  Virtuelle
##  Polytech 2019-2020
##
##  leo.donati@univ-cotedazur.fr
##
##  Tuto1
##
##############################################

varying highp vec4 outColor;

void main(void)
{
    float  opacity = outColor.a;
    vec3 color = outColor.rgb * (1 - gl_FragCoord.z);
    gl_FragColor = vec4(color,opacity);
}
