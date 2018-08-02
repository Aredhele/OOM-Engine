#version 330 core

// In
layout(location = 0) in vec3 vertex;
layout(location = 2) in vec2 vertexUV;

// Out
out vec2 UV;

void main(){

	// Output position of the vertex, in clip space
	// map [0..800][0..600] to [-1..1][-1..1]
	// [0..800][0..600] -> [-400..400][-300..300]
		// 1600 - 900
	vec2 vertexPosition_homoneneousspace = vec2(vertex.x, vertex.y) - vec2(900, 450);
    	vertexPosition_homoneneousspace /= vec2(900, 450);


	//vec2 vertexPosition_homoneneousspace = vec2(vertex.x, vertex.y) - vec2(400,300);
	//vertexPosition_homoneneousspace /= vec2(400,300);
	gl_Position =  vec4(vertexPosition_homoneneousspace,0,1);

	UV = vec2(vertexUV.x, vertexUV.y);
}

