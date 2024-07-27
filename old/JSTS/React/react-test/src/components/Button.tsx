interface ButtonProps {
  children: string;
  color?: string; // ? -> signifies optional
  // alternately, to set a default value:
  // color?: 'primary' | 'secondary' | 'other valid options'
  onClick: () => void;
}

const Button = ({ children, color = "primary", onClick }: ButtonProps) => {
  return (
    <button className={"btn btn-" + color} onClick={onClick}>
      {children}
    </button>
  );
};

export default Button;
