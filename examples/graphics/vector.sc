/**
 * Provides a vector structure and accompanying functions.
 *
 * Copyright (c) Blake Loring 2013
 */
 
package sys := import("sys");

/**
 * Vector3 structure takes 3 floating points as variables x, y and z
 */

type Vector3 := struct {
	x : float32;
	y : float32;
	z : float32;
}

/**
 * Compute the addition of two vectors and return a new structure containing the result.
 */

func Add(left : Vector3, right : Vector3) : Vector3 {
	
	return Vector3{
		left->x + right->x,
		left->y + right->y,
		left->z + right->z
	};

}

/**
 * Compute the subtraction of two vectors and return a new structure containing the result.
 */

func Subtract(left : Vector3, right : Vector3) : Vector3 {
	
	return Vector3 {
		left->x - right->x,
		left->y - right->y,
		left->z - right->z
	};

}

/**
 * Compute the cross product of vectors left and right and return a new structure containing the result.
 */

func Cross(left : Vector3, right : Vector3) : Vector3 {

	return Vector3 {
		left->y * right->z,
		left->z * right->x,
		left->x * right->y
	};

}

/**
 * Return the dot product of two vectors as a float.
 */

func Dot(left : Vector3, right : Vector3) : float32 {
	return (left->x * right->x) + (left->y * right->y) + (left->z * right->z);
}

/**
 * Print information about a given vector to the command line.
 */

func Debug(v : Vector3) {
	sys.Write("X: ");
	sys.Write(sys.String(v->x));
	sys.Write(" Y: ");
	sys.Write(sys.String(v->y));
	sys.Write(" Z: ");
	sys.Write(sys.String(v->z));
	sys.Write("\n");	
}