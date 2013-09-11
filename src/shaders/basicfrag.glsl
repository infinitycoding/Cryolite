uniform sampler2D texSampler;

void main(void)
{
    gl_FragColor = texture2D(texSampler, vec2(gl_TexCoord[0]));
    gl_FragColor += gl_fragDepth;
}
